/* -----------------------------------------------------------------------------
  Filename:    ccl_par.c
  Description: Toolversion: 02.03.11.01.70.09.79.00.00.00
               
               Serial Number: CBD1700979
               Customer Info: Huizhou Desay SV Automotive Co., Ltd.
                              Package: CBD_Vector_SLP2
                              Micro: R7F7016213AFP
                              Compiler: Green Hills 2015.1.7
               
               
               Generator Fwk   : GENy 
               Generator Module: Ccl__core
               
               Configuration   : D:\Renesas_Platform\FAWHQ_C205_Source\FAWHQ_C205_AVM_MCU\Source\vicp\ComplexDriver\CANdriver\tool\CBD1700979 D00 Rh850 GreenHills FAW C205.gny
               
               ECU: 
                       TargetSystem: Hw_Rh850Cpu
                       Compiler:     GreenHills
                       Derivates:    F1L
               
               Channel "Channel0":
                       Databasefile: D:\Renesas_Platform\FAWHQ_C205_Source\FAWHQ_C205_AVM_MCU\Source\vicp\ComplexDriver\CANdriver\tool\ab02_979_C205_CAN1_V0.1_20191120.dbc
                       Bussystem:    CAN
                       Manufacturer: Vector
                       Node:         AVS

 ----------------------------------------------------------------------------- */
/* -----------------------------------------------------------------------------
  C O P Y R I G H T
 -------------------------------------------------------------------------------
  Copyright (c) 2001-2015 by Vector Informatik GmbH. All rights reserved.
 
  This software is copyright protected and proprietary to Vector Informatik 
  GmbH.
  
  Vector Informatik GmbH grants to you only those rights as set out in the 
  license conditions.
  
  All other rights remain with Vector Informatik GmbH.
 -------------------------------------------------------------------------------
 ----------------------------------------------------------------------------- */

#define CCL_PAR_MODULE
#include "ccl_inc.h"
#include "ccl_par.h"

/******************************************************************************/
/* function external declaration                                              */
/******************************************************************************/



/******************************************************************************/
/* internal declarations (ROM const)                                          */
/******************************************************************************/
/******************************************************************************/
/* external declarations (ROM const)                                          */
/******************************************************************************/
V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 cclNmWakeUpAble = 0x1;   /* The variable store the wake up able channels (one bit per channel). */
V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 cclStartIndex[1] = {
    0
};

V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 cclStopIndex[1] = {
    0
};
V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 cclUserOffset[kCclNumberOfUser] = {
      0x0,   0x0
};

V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 cclUserMask[kCclNumberOfUser] = {
      0x1,   0x2
};

V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 cclUserChannel[kCclNumberOfUser] = {
    0x0, 0x0
};
/******************************************************************************/
/* global data definitions                                                    */
/******************************************************************************/
/***************************************************************************** 
| NAME:             CclInitPowerOnFct                                          
| PROTOTYPE:        void CclInitPowerOnFct( void )                             
| CALLED BY:        CclInitPowerOn                                             
| PRECONDITIONS:    Application is NOT ALLOWED to call this function!          
| INPUT PARAMETERS: void                                                       
| RETURN VALUE:     void                                                       
| DESCRIPTION:      This function is a generated init container function. It   
|                   contains different init routines depending on the          
|                   used modules.                                              
|*****************************************************************************/

void CclInitPowerOnFct(void)
{
  CanNm_InitMemory();
  #if defined(C_SINGLE_RECEIVE_CHANNEL) || defined(C_MULTIPLE_RECEIVE_CHANNEL)
    CanInitPowerOn();
  #else
    CanInitPowerOn(0);
  #endif
  IlInitPowerOn();
  Nm_Init(NULL_PTR);
  CanNm_Init(NULL_PTR);
  CbdWrpInit(0);
  TpInitPowerOn();
  DescInitPowerOn(kDescPowerOnInitParam);
}
/***************************************************************************** 
| NAME:             CclInitFct                                                 
| PROTOTYPE:        void CclInitFct( void )                                    
| CALLED BY:        CclInit                                                    
| PRECONDITIONS:    Application is NOT ALLOWED to call this function!          
| INPUT PARAMETERS: void                                                       
| RETURN VALUE:     void                                                       
| DESCRIPTION:      This function is a generated init container function. It   
|                   contains different init routines depending on the          
|                   used modules.                                              
|*****************************************************************************/

void CclInitFct(void)
{
#if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  CanInit(0, 0);
#else
  CanInit(0);
#endif
  IlInit();
  Nm_Init(NULL_PTR);
  CanNm_Init(NULL_PTR);
  CbdWrpInit(0);
  ApplCclInit();
}

/**************************************************************************************
| NAME:             CclSystemShutdownFct                                               
| PROTOTYPE:        void CclSystemShutdownFct( void )                                  
| CALLED BY:        CclSystemShutdown                                                  
| PRECONDITIONS:    Application is NOT ALLOWED to call this function!                  
| INPUT PARAMETERS: void                                                               
| RETURN VALUE:     void                                                               
| DESCRIPTION:      This function is a generated system shutdown container             
|                   function. It could be used to stop services or deinitialize        
|                   variables after the system leaves the "normal" mode.             
|*************************************************************************************/

void CclSystemShutdownFct(void) 
{ 
  ApplCclSleepTrcv();
}


/****************************************************************************************
| NAME:             CclScheduleTask                                                      
| PROTOTYPE:        void CclScheduleTask                                                 
| CALLED BY:        task handler                                                         
| PRECONDITIONS:    has to be called every 10ms                                           
| INPUT PARAMETERS: void                                                                 
| RETURN VALUE:     void                                                                 
| DESCRIPTION:      This function is a generated schedule task. This task call all other 
|                   task with in the right task cycle + offset.                          
|***************************************************************************************/
void CCL_API_CALL_TYPE CclScheduleTask(void)
{ 
  IlTxTask();

  IlRxTask(); 

  CclTask();

  CanNm_MainFunction_0();

  CbdWrpTask(0);

   TpRxTask();

  DescTask();

   TpTxTask();



}

/******************************************************************************
| NAME:             CclComStart                                                
| PROTOTYPE:        void CclComStart(void)                                  
| CALLED BY:        network management                                         
| PRECONDITIONS:    Application is NOT ALLOWED to call this function!          
| INPUT PARAMETERS:                                                            
| RETURN VALUE:     void                                                       
| DESCRIPTION:      This function start the communication with interaction layer.
|*****************************************************************************/
void CclComStart(void)
{
  cclComSwState[0]=kCclComSwOn;
  ApplCclComStart();
    IlTxStart();
  IlRxStart();
}
/******************************************************************************
| NAME:             CclComStop                                                 
| PROTOTYPE:        void CclComStop(void)                                      
| CALLED BY:        network management                                         
| PRECONDITIONS:    Application is NOT ALLOWED to call this function!          
| INPUT PARAMETERS:                                                            
| RETURN VALUE:     void                                                       
| DESCRIPTION:      This function stop the communication with interaction layer.
|*****************************************************************************/
void CclComStop(void)
{
  IlTxStop();
  IlRxStop();
  cclComSwState[0]=kCclComSwOff;
  ApplCclComStop();
}
/******************************************************************************
| NAME:             CclComWait                                                
| PROTOTYPE:        void CclComWait(void)                                  
| CALLED BY:        network management                                         
| PRECONDITIONS:    Application is NOT ALLOWED to call this function!          
| INPUT PARAMETERS:                                                            
| RETURN VALUE:     void                                                       
| DESCRIPTION:      This function sets the interaction layer into the wait state.
|*****************************************************************************/
void CclComWait(void)
{
  cclComSwState[0]=kCclComSwOff;
  ApplCclComWait();
  IlTxWait();
  IlRxWait();
}
/******************************************************************************
| NAME:             CclComResume                                                 
| PROTOTYPE:        void CclComResume(void)                                      
| CALLED BY:        network management                                         
| PRECONDITIONS:    Application is NOT ALLOWED to call this function!          
| INPUT PARAMETERS:                                                            
| RETURN VALUE:     void                                                       
| DESCRIPTION:      This function resumes the communication with interaction layer.
|*****************************************************************************/
void CclComResume(void)
{
    IlTxRelease();
  IlRxRelease();
  cclComSwState[0]=kCclComSwOn;
  ApplCclComResume();
}






/******************************************************************************
| NAME:             CclBusOffStart                                             
| PROTOTYPE:        void CclBusOffStart(void)                                  
| CALLED BY:        network management                                         
| PRECONDITIONS:    Application is NOT ALLOWED to call this function!          
| INPUT PARAMETERS:                                          ,                 
| RETURN VALUE:     void                                                       
| DESCRIPTION:      This function stop the communication with interaction layer.
|*****************************************************************************/
void CclBusOffStart(void)
{
  #if defined( CCL_ENABLE_STOP_TIMEOUT)
    //IlTxWait();
    //IlRxWait();
    IlTxStop();
    IlRxStop();
  #endif
  ApplCclBusOffStart();
}
/******************************************************************************
| NAME:             CclBusOffEnd                                               
| PROTOTYPE:        void CclBusOffEnd(void)                                    
| CALLED BY:        network management                                         
| PRECONDITIONS:    Application is NOT ALLOWED to call this function!          
| INPUT PARAMETERS:                                                            
| RETURN VALUE:     void                                                       
| DESCRIPTION:      This function start the communication with interaction layer.
|*****************************************************************************/
void CclBusOffEnd(void)
{
  #if defined(CCL_ENABLE_STOP_TIMEOUT)
    //IlTxRelease();
    //IlRxRelease();
    IlTxStart();
    IlRxStart();
  #endif
  ApplCclBusOffEnd();
}

/**********************************************************************************
| NAME:             CclNmActiveReqFct                                              
| PROTOTYPE:        vuint8 CclNmActiveReqFct( vuint8 network )                     
| CALLED BY:        CclTask                                                        
| PRECONDITIONS:    Application is NOT ALLOWED to call this function!              
| INPUT PARAMETERS: vuint8 network                                                 
| RETURN VALUE:     vuint8                                                         
| DESCRIPTION:      This function contains the algorithm to go in the active       
|                   mode. The algorithm depends on the used modules.               
|*********************************************************************************/

vuint8 CclNmActiveReqFct(vuint8 network)
{
#if defined V_ENABLE_USE_DUMMY_STATEMENT
  network = network;

#endif
  (void)Nm_NetworkRequest((NetworkHandleType)0);
  return NM_OK;
}
/***********************************************************************************
| NAME:             CclNmPrepareSleepReqFct                                          
| PROTOTYPE:        void CclNmPrepareSleepReqFct( void )                             
| CALLED BY:        CclTask                                                          
| PRECONDITIONS:    Application is NOT ALLOWED to call this function!                
| INPUT PARAMETERS: void                                                             
| RETURN VALUE:     void                                                             
| DESCRIPTION:      This function contains the algorithm to set the system in        
|                   prepare sleep mode. The algorithm depends on the used            
|                   modules.                                                         
|***********************************************************************************/

void CclNmPrepareSleepReqFct(void)
{
  (void)Nm_PassiveStartUp((NetworkHandleType)0);
}
/***********************************************************************************
| NAME:             CclNmSleepReqFct                                                
| PROTOTYPE:        void CclNmSleepReqFct( vuint8 network )                         
| CALLED BY:        CclRelNetRequest                                                
| PRECONDITIONS:    Application is NOT ALLOWED to call this function!               
| INPUT PARAMETERS: vuint8 network                                                  
| RETURN VALUE:     void                                                            
| DESCRIPTION:      This function contains the algorithm to go in the sleep         
|                   mode. The algorithm depends on the used modules.                
|**********************************************************************************/
void CclNmSleepReqFct(vuint8 network)
{
#if defined V_ENABLE_USE_DUMMY_STATEMENT
  network = network;

#endif
  (void)Nm_NetworkRelease((NetworkHandleType)0);
}





/********************************************************************************
| NAME:             CclInitTrcvFct                                              
| PROTOTYPE:        void CclInitTrcvFct( void )                                 
| CALLED BY:        CclInitPortsPowerOn                                          
| PRECONDITIONS:    Application is NOT ALLOWED to call this function!            
| INPUT PARAMETERS: void                                                         
| RETURN VALUE:     void                                                         
| DESCRIPTION:      This function contains the transceiver init routine.         
|                   The routine depends on the used transceiver type.            
|*******************************************************************************/

void CclInitTrcvFct(void)
{
  ApplCclInitTrcv();
}
/************************************************************************************
| NAME:             CclWakeUpTrcvFct                                                
| PROTOTYPE:        void CclWakeUpTrcvFct( void )                                   
| CALLED BY:        ApplNmCanNormal                                                  
| PRECONDITIONS:    Application is NOT ALLOWED to call this function!                
| INPUT PARAMETERS: void                                                             
| RETURN VALUE:     void                                                             
| DESCRIPTION:      This function contains the routine to wakeup the                 
|                   transceiver. The routine depends on the used transceiver         
|                   type.                                                            
|***********************************************************************************/

void CclWakeUpTrcvFct(void)
{ 
  ApplCclWakeUpTrcv();
}
/************************************************************************************
| NAME:             CclSleepTrcvFct                                                 
| PROTOTYPE:        void CclSleepTrcvFct( void )                                    
| CALLED BY:        ApplNmCanSleep                                                   
| PRECONDITIONS:    Application is NOT ALLOWED to call this function!                
| INPUT PARAMETERS: void                                                             
| RETURN VALUE:     void                                                             
| DESCRIPTION:      This function contains the routine to switch the                 
|                   transceiver into sleep mode. The routine depends on              
|                   the used transceiver type.                                       
|***********************************************************************************/

void CclSleepTrcvFct(void)
{
  ApplCclStandbyTrcv();
}














/* begin Fileversion check */
#ifndef SKIP_MAGIC_NUMBER
#ifdef MAGIC_NUMBER
  #if MAGIC_NUMBER != 335188586
      #error "The magic number of the generated file <D:\Renesas_Platform\FAWHQ_C205_Source\FAWHQ_C205_AVM_MCU\Source\vicp\ComplexDriver\CANdriver\tool\gen979\ccl_par.c> is different. Please check time and date of generated files!"
  #endif
#else
  #error "The magic number is not defined in the generated file <D:\Renesas_Platform\FAWHQ_C205_Source\FAWHQ_C205_AVM_MCU\Source\vicp\ComplexDriver\CANdriver\tool\gen979\ccl_par.c> "

#endif  /* MAGIC_NUMBER */
#endif  /* SKIP_MAGIC_NUMBER */

/* end Fileversion check */


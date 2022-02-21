/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.				   *
*				  All Rights Reserved.          					   *
*   Department : CT AD     									   *
*   AUTHOR	   : 									   *
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
* 
*=====================================================================*/
/**** Definition of constants ****/

/**** Definition of macros ****/
/**** Declaration of constants ****/
/**** Declaration of variables ****/
#include "can_app_il.h"
/**** Declaration of functions ****/
//TX signal define
#ifdef CANTXSIG_PASS_1
    #undef CANTXSIG_PASS_1
    #define BEGIN_CANTXSIGDESCS       typedef enum {
    #define END_CANTXSIGDESCS         CAN_NUM_OF_TX_SIG_ID}E_CAN_TX_SIG_ID;
    #define CANTXSIGDESC(x,y,z)   x,	
   #include "Cansig_cfg.h"
#endif

#ifdef CANTXSIG_PASS_2
    #undef CANTXSIG_PASS_2
    #define BEGIN_CANTXSIGDESCS       
    #define END_CANTXSIGDESCS        
    #define CANTXSIGDESC(x,y,z)      TX_SIG_SET_FUNC(y);
   #include "Cansig_cfg.h"
#endif

#ifdef CANTXSIG_PASS_3
    #undef CANTXSIG_PASS_3
    #define BEGIN_CANTXSIGDESCS       const CAN_TX_SIG_FUNC_MAP CANTxSigFuncMap[CAN_NUM_OF_TX_SIG_ID] ={
    #define END_CANTXSIGDESCS         };
    #define CANTXSIGDESC(x,y,z)      TX_SIG_SET_FUNC_REF(y),	
   #include "Cansig_cfg.h"
#endif

#ifdef CANTXSIG_PASS_4
    #undef CANTXSIG_PASS_4
    #define BEGIN_CANTXSIGDESCS      
    #define END_CANTXSIGDESCS         
    #define CANTXSIGDESC(x,y,z)   extern TX_SIG_SET_FUNC(y);\
								TX_SIG_SET_FUNC(y){\
								IlPutTx##y(pSignalInfo->SignalData.##z);};
   #include "Cansig_cfg.h"
#endif


//RX signal define
#ifdef CANRXSIG_PASS_1
    #undef CANRXSIG_PASS_1
    #define BEGIN_CANRXSIGDESCS       typedef enum {
    #define END_CANRXSIGDESCS         CAN_NUM_OF_RX_SIG_ID}E_CAN_RX_SIG_ID;
    #define CANRXSIGDESC(x,y,z)   x,    
    #define CANRXSIGDESC_B(x,y,z) x,
    #define CANRXSIGDESC_TO(x,y,z) x,
   #include "Cansig_cfg.h"
#endif

#ifdef CANRXSIG_PASS_2
    #undef CANRXSIG_PASS_2
    #define BEGIN_CANRXSIGDESCS       
    #define END_CANRXSIGDESCS        
    #define CANRXSIGDESC(x,y,z)     RX_SIG_GET_FUNC(y);
    #define CANRXSIGDESC_B(x,y,z)  RX_SIG_GET_FUNC(y);   
    #define CANRXSIGDESC_TO(x,y,z)  RX_SIG_GET_FUNC(y);   
   #include "Cansig_cfg.h"
#endif

#ifdef CANRXSIG_PASS_3
    #undef CANRXSIG_PASS_3
    #define BEGIN_CANRXSIGDESCS       const CAN_RX_SIG_FUNC_MAP CANRxSigFuncMap[CAN_NUM_OF_RX_SIG_ID] ={
    #define END_CANRXSIGDESCS         };
    #define CANRXSIGDESC(x,y,z)     RX_SIG_GET_FUNC_REF(y),
    #define CANRXSIGDESC_B(x,y,z) RX_SIG_GET_FUNC_REF(y),    
    #define CANRXSIGDESC_TO(x,y,z) RX_SIG_GET_FUNC_REF(y),    
   #include "Cansig_cfg.h"
#endif

#ifdef CANRXSIG_PASS_4
    #undef CANRXSIG_PASS_4
    #define BEGIN_CANRXSIGDESCS       
    #define END_CANRXSIGDESCS         
    #define CANRXSIGDESC(x,y,z)    extern RX_SIG_GET_FUNC(y);\
								RX_SIG_GET_FUNC(y){\
								pSignalInfo->SignalData.##z = IlGetRx##y();};	

    #define CANRXSIGDESC_B(x,y,z)	 extern RX_SIG_GET_FUNC(y);\
								RX_SIG_GET_FUNC(y){\
								IlGetRx##y(pSignalInfo->SignalData.##z);};	
								
    #define CANRXSIGDESC_TO(x,y,z)    extern RX_SIG_GET_FUNC(y);\
								RX_SIG_GET_FUNC(y){\
								pSignalInfo->SignalData.##z = IlGet##y();};	
   #include "Cansig_cfg.h"
#endif

//if (z == pDataBuf) IlGetRx##y(pSignalInfo->SignalData.##z)
//pSignalInfo->SignalData.Data8U = IlGetRxCrashOutputSts()

/****************************** END OF FILE ***************************/


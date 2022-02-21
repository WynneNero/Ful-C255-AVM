/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.				   *
*				  All Rights Reserved.          					   *
*   Department : RN R&D SW1      									   *
*   AUTHOR	   :            										   *
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

/**** System include files ****/
#include "CONFIG.H"
#include "TYPES.H"   

/*---Public include files---------------------------------------------*/
//#include "TPMC.H"
 #include "CAN_CFG.H"
 #include "V_DEF.H"
 #include "CAN_DEF.H"
 #include "IL_INC.H"
//#include "nm_osek.h" /* if it is a OSEK NM */
#include "CanManager_if.h"

/*---Private include files--------------------------------------------*/
#include "CAN_APP_DRV.H"   
#include "CAN_APP_DRV_IF.H" 
#include "candriver_if.h"

/*===VARIABLES========================================================*/

/*---Global-----------------------------------------------------------*/

/*---Private----------------------------------------------------------*/

/*===FUNCTIONS========================================================*/

/*---Global-----------------------------------------------------------*/
//BOOL bCanBusBusoff = FALSE;



/***********************************************************************
* FUNCTION    : void ApplVStdFatalError(vuint8 nErrorNumber)
* DESCRIPTION : 
* INPUTS      : none
* RETURN      : none
***********************************************************************/
void ApplVStdFatalError(vuint8 nErrorNumber)
{
    
}


/***********************************************************************
* FUNCTION    : void ApplCanBusOff(CanChannelHandle channel)
* DESCRIPTION : 
* INPUTS      : none
* RETURN      : none
***********************************************************************/
static U8 bBusOFFChannel;
//void CanAppBusOff(CanChannelHandle channel)
//{
//    /* save bus off channel for calling timer function to enable sending function */
//    bBusOFFChannel = channel;
//
//    CanInit(channel);
//
//    bCanBusBusoff = TRUE;
//
//    IlTxWait();
//
//    //Timer_Start(ENABLE_CAN_SENDING,100,TIMER_ONE_SHOT);
//}

//void CanManager_BusOffEnd(void)
//{
//    IlTxStart();
//}

/***********************************************************************
* FUNCTION    : void CanManagerTxConfirmation(void)
* DESCRIPTION : If successful send CAN message, will enter this callback function
* INPUTS      : none
* RETURN      : none
***********************************************************************/
//void CanManagerTxConfirmation(void)
//{
//    if(bCanBusBusoff)
//    {
//        bCanBusBusoff = FALSE;
//    }
//
//    /* for can diag bus off dtc */
//    can_diag_reset_bus_off_counter();
//}


/***********************************************************************
* FUNCTION    : void ApplNmBusOff(void)
* DESCRIPTION : 
* INPUTS      : none
* RETURN      : none
***********************************************************************/
#ifndef ApplCanBusOff
//void ApplNmBusOff(void)
//{
//    #ifndef CAN_NM_OPTION
//    CanManager_BusOffStart();
//    #else
//    CanDriver_SetBusOffState(TRUE);
//    #endif
//}
#endif /* ApplCanBusOff */

/***********************************************************************
* FUNCTION    : void ApplCanWakeUp(void)
* DESCRIPTION : 
* INPUTS      : none
* RETURN      : none
***********************************************************************/
//#ifndef ApplCanWakeUp
//void ApplCanWakeUp(void)
//{
//}
//#endif /* ApplCanWakeUp */

/***********************************************************************
* FUNCTION    : void ApplCanOverrun(void)
* DESCRIPTION : 
* INPUTS      : none
* RETURN      : none
***********************************************************************/
#if defined (C_ENABLE_OVERRUN)
void ApplCanOverrun(void)
{
    CanDriver_SetBusOffState(TRUE);
}
#endif /* C_ENABLE_OVERRUN */

/***********************************************************************
* FUNCTION    : void ApplCanFullCanOverrun(void)
* DESCRIPTION : 
* INPUTS      : none
* RETURN      : none
***********************************************************************/
#if defined (C_ENABLE_FULLCAN_OVERRUN)
void ApplCanFullCanOverrun(void)
{
    CanDriver_SetBusOffState(TRUE);
}
#endif /* C_ENABLE_FULLCAN_OVERRUN */

/***********************************************************************
* FUNCTION    : vuint8 ApplCanRangePrecopy(CanRxInfoStructPtr rxStruct)
* DESCRIPTION : 
* INPUTS      : none
* RETURN      : none
***********************************************************************/
#if defined (C_ENABLE_RANGE)
vuint8 ApplCanRangePrecopy(CanRxInfoStructPtr rxStruct)
{
    return kCanCopyData; 
}
#endif /* C_ENABLE_RANGE */

/***********************************************************************
* FUNCTION    : void ApplCanFatalError(canuint8 errorNumber)
* DESCRIPTION : 
* INPUTS      : none
* RETURN      : none
***********************************************************************/
#if defined (C_ENABLE_HARDWARE_CHECK) || \
    defined (C_ENABLE_USER_CHECK) || \
    defined (C_ENABLE_GEN_CHECK) || \
    defined (C_ENABLE_INTERNAL_CHECK)
void ApplCanFatalError(canuint8 errorNumber)
{
    CanDriver_SetBusOffState(TRUE);
}
#endif /* C_ENABLE_HARDWARE_CHECK | \
        C_ENABLE_USER_CHECK | \
        C_ENABLE_GEN_CHECK | \
        C_ENABLE_INTERNAL_CHECK */

/***********************************************************************
* FUNCTION    : void ApplCanMsgNotMatched(CanRxInfoStructPtr rxStruct)
* DESCRIPTION : 
* INPUTS      : none
* RETURN      : none
***********************************************************************/
#if defined (C_ENABLE_NOT_MATCHED_FCT)
void ApplCanMsgNotMatched(CanRxInfoStructPtr rxStruct)
{
}
#endif /* C_ENABLE_NOT_MATCHED_FCT */

/***********************************************************************
* FUNCTION    : void ApplCanInit(CanObjectHandle txHwObjectFirstUsed,
                        CanObjectHandle txHwObjectFirstUnused)
* DESCRIPTION : 
* INPUTS      : none
* RETURN      : none
***********************************************************************/
#if defined (C_ENABLE_TX_OBSERVE)
void ApplCanInit(CanObjectHandle txHwObjectFirstUsed,
                        CanObjectHandle txHwObjectFirstUnused)
{
}
#endif /* C_ENABLE_TX_OBSERVE */

/***********************************************************************
* FUNCTION    : void ApplCanTxObjStart(CanObjectHandle txHwObject)
* DESCRIPTION : 
* INPUTS      : none
* RETURN      : none
***********************************************************************/
#if defined (C_ENABLE_TX_OBSERVE)
void ApplCanTxObjStart(CanObjectHandle txHwObject)
{
}
#endif /* C_ENABLE_TX_OBSERVE */

/***********************************************************************
* FUNCTION    : void ApplCanTxObjConfirmed(CanObjectHandle txHwObject)
* DESCRIPTION : 
* INPUTS      : none
* RETURN      : none
***********************************************************************/
#if defined (C_ENABLE_TX_OBSERVE)
void ApplCanTxObjConfirmed(CanObjectHandle txHwObject)
{
}
#endif /* C_ENABLE_TX_OBSERVE */

/***********************************************************************
* FUNCTION    : canuint8 ApplCanGenericPrecopy(CanReceiveHandle rxHandle,
                                                CanChipDataPtr rxObject)
* DESCRIPTION : 
* INPUTS      : none
* RETURN      : none
***********************************************************************/
#if defined (C_ENABLE_GENERIC_PRECOPY)
#ifndef APPL_CAN_GENERIC_PRECOPY
canuint8 ApplCanGenericPrecopy(CanReceiveHandle rxHandle,
                                                CanChipDataPtr rxObject)
{
    return kCanCopyData; 
}
#endif /* APPL_CAN_GENERIC_PRECOPY */
#endif /* C_ENABLE_GENERIC_PRECOPY */

/***********************************************************************
* FUNCTION    : void ApplCanTxConfirmation(CanTxInfoStructPtr txStruct)
* DESCRIPTION : 
* INPUTS      : none
* RETURN      : none
***********************************************************************/
//#if defined (C_ENABLE_CAN_TX_CONF_FCT)
//void ApplCanTxConfirmation(CanTxInfoStructPtr txStruct)
//{
//    CanManagerTxConfirmation();
//}
//#endif /* C_ENABLE_CAN_TX_CONF_FCT */

/***********************************************************************
* FUNCTION    : void ApplCanMsgDlcFailed(CanRxInfoStructPtr rxStruct)
* DESCRIPTION : 
* INPUTS      : none
* RETURN      : none
***********************************************************************/
#if defined (C_ENABLE_DLC_FAILED_FCT)
void ApplCanMsgDlcFailed(CanRxInfoStructPtr rxStruct)
{
}
#endif /* C_ENABLE_DLC_CHECK */

/***********************************************************************
* FUNCTION    : void ApplCanMsgTransmitConf(void)
* DESCRIPTION : 
* INPUTS      : none
* RETURN      : none
***********************************************************************/
#if defined (C_ENABLE_MSG_TRANSMIT_CONF_FCT)
void ApplCanMsgTransmitConf(void)
{
}
#endif /* C_ENABLE_MSG_TRANSMIT_CONF_FCT */ 

/***********************************************************************
* FUNCTION    : void ApplCanMsgTransmitInit(void)
* DESCRIPTION : 
* INPUTS      : none
* RETURN      : none
***********************************************************************/
#if defined (C_ENABLE_MSG_TRANSMIT_CONF_FCT)
void ApplCanMsgTransmitInit(void)
{
}
#endif /* C_ENABLE_MSG_TRANSMIT_CONF_FCT */
/***********************************************************************
* FUNCTION    : void ApplCanInterruptDisable(void)
* DESCRIPTION : 
* INPUTS      : none
* RETURN      : none
***********************************************************************/
#if defined(VSTD_ENABLE_APPL_INTCTRL)
void ApplCanInterruptDisable(void)
{
    can_irq_disable();
}
#endif /* VSTD_ENABLE_APPL_INTCTRL */

/***********************************************************************
* FUNCTION    : void ApplCanInterruptRestore(void)
* DESCRIPTION : 
* INPUTS      : none
* RETURN      : none
***********************************************************************/
#if defined(VSTD_ENABLE_APPL_INTCTRL)
void ApplCanInterruptRestore(void)
{
    can_irq_enable();
}
#endif /* VSTD_ENABLE_APPL_INTCTRL */

/*---Private----------------------------------------------------------*/

#define kNormalAddressingTxId           0x72E
#define kNormalAddressingPhysRxId       0x726
#define kNormalAddressingIpcRxId        0x44B
#define kNormalAddressingTpHutTxId      0x448
#define kmyConectionNumber 1
#define kmyConectionNumber1 2


extern tTpRxInfoStruct tpRxInfoStruct[];
volatile void *retPtr;
U8 IpcRxTest;
U8 testBuf[200];


/***********************************************************************
* FUNCTION    : unsigned char* ApplTpRxGetBuffer(vuint8 tpChannel, vuint16 tpRxDataLength)
* DESCRIPTION : 
* INPUTS      : none
* RETURN      : none
***********************************************************************/
unsigned char* ApplTpRxGetBuffer(vuint8 tpChannel, vuint16 tpRxDataLength)
{
    U16 requestId = TpRxGetChannelID(tpChannel);
    retPtr = V_NULL;

    if(kNormalAddressingIpcRxId == requestId)
        {
            IpcRxTest++;
            retPtr = testBuf;

            if(retPtr!= V_NULL)
            {
                if((TpRxGetAddressingFormat(tpChannel) == kTpNormalAddressing)) 
                { 
                    TpRxSetTransmitID(tpChannel, kNormalAddressingTpHutTxId);
                }
            }
        }
        else
        {       
            retPtr = DescGetBuffer(tpChannel,tpRxDataLength); 
            
            if(retPtr != V_NULL) 
            { 
    
                if((TpRxGetAddressingFormat(tpChannel) == kTpNormalAddressing)) 
                { 
                    TpRxSetTransmitID(tpChannel, kNormalAddressingTxId); 
                } 
    
            } 
        }
      return (canuint8*)retPtr; 

}


/***********************************************************************
* FUNCTION    : void ApplTpRxIndication(vuint8 tpChannel, vuint16 tpRxDataLength)
* DESCRIPTION : 
* INPUTS      : none
* RETURN      : none
***********************************************************************/
void ApplTpRxIndication(vuint8 tpChannel, vuint16 tpRxDataLength)
{
    vuint8 addressingType= (TpRxGetAddressingFormat(tpChannel)); 
	U16 requestId = TpRxGetChannelID(tpChannel);
	
	if(kNormalAddressingIpcRxId == requestId)
	{
        /* Set CAN IDs for the Response*/ 
		if((addressingType == kTpNormalAddressing)) 
		{ 
			TpTxSetChannelID(tpChannel, kNormalAddressingTpHutTxId, kNormalAddressingIpcRxId); 
		}
	}
	else
	{

		DescPhysReqInd(tpChannel, tpRxDataLength);

	    /* Set CAN IDs for the Response*/ 
		if((addressingType == kTpNormalAddressing)) 
		{ 
			TpTxSetChannelID(tpChannel, kNormalAddressingTxId, kNormalAddressingPhysRxId); 
		}
	}

/*
    switch(TpRxGetConnectionNumber(tpChannel))
    {
        case kDiagConnection:
            DiagPhysReception(tpChannel, tpRxDataLength);
        break;
        case CONNECTION_0:
            UserTpRxIndication(tpRxDataLength);
        break;
            default:
            break;
    }
    */
}


/***********************************************************************
* FUNCTION    : void ApplTpRxErrorIndication(vuint8 tpChannel, vuint8 status)
* DESCRIPTION : 
* INPUTS      : none
* RETURN      : none
***********************************************************************/
void ApplTpRxErrorIndication(vuint8 tpChannel, vuint8 status)
{
    DescRxErrorIndication(0,status);
/*
    switch(TpRxGetConnectionNumber(tpChannel))
    {
        case kDiagConnection:
            DiagRxErrorIndication(tpChannel, status);
        case CONNECTION_0:
            UserTpRxErrorIndication(status);
        default:
            break;
    }
    */
}


/***********************************************************************
* FUNCTION    : void ApplTpRxFF(vuint8 tpChannel)
* DESCRIPTION : 
* INPUTS      : none
* RETURN      : none
***********************************************************************/
void ApplTpRxFF(vuint8 tpChannel)
{/*
    if (TpRxGetConnectionNumber( tpChannel ) == kDiagConnection )
    {
        DiagRestartS1TimerInternal( tpChannel );
    }
    */
}


/***********************************************************************
* FUNCTION    : void ApplTpRxFF(vuint8 tpChannel)
* DESCRIPTION : 
* INPUTS      : none
* RETURN      : none
***********************************************************************/
void ApplTpRxCF(vuint8 tpChannel)
{/*
    if (TpRxGetConnectionNumber( tpChannel ) == kDiagConnection )
    {
        DiagRestartS1TimerInternal( tpChannel );
    }
    */
}


/***********************************************************************
* FUNCTION    : void ApplTpTxConfirmation(vuint8 tpChannel, vuint8 state)
* DESCRIPTION : 
* INPUTS      : none
* RETURN      : none
***********************************************************************/
void ApplTpTxConfirmation(vuint8 tpChannel, vuint8 state)
{
    U16 CurrentConection = TpTxGetConnectionNumber(tpChannel);
	
	if(kmyConectionNumber == CurrentConection)
	{

	}
	else
	{
		DescConfirmation(tpChannel,state);
	}
    
/*
    switch(TpTxGetConnectionNumber(tpChannel))
    {
        case kDiagConnection:
            DiagConfirmation( tpChannel, state);
        case CONNECTION_0:
            UserTpConfirmation(status);
        default:
            break;
    }
    */
}


/***********************************************************************
* FUNCTION    : vuint8 ApplTxErrorIndication(vuint8 tpChannel, vuint8 status)
* DESCRIPTION : 
* INPUTS      : none
* RETURN      : none
***********************************************************************/
vuint8 ApplTxErrorIndication(canuint8 tpChannel, canuint8 state)
{

    U16 CurrentConection = TpTxGetConnectionNumber(tpChannel);
	
	if(kmyConectionNumber == CurrentConection)
	{

	}
	else
	{
		DescTxErrorIndication(tpChannel,state);
	}
	return 0; 

/*
    switch(TpTxGetConnectionNumber(tpChannel))
    {
        case kDiagConnection:
            return DiagTxErrorIndication(tpChannel, status);
        case CONNECTION_0:
            UserTpTxErrorIndication(status);
        default:
            return kTpFreeChannel;
    }
    */
}


/***********************************************************************
* FUNCTION    : vuint8 ApplCopyToCAN(TpCopyToCanInfoStructPtr infoStruct)
* DESCRIPTION : 
* INPUTS      : none
* RETURN      : none
***********************************************************************/
vuint8 ApplCopyToCAN(TpCopyToCanInfoStructPtr infoStruct)
{
    //switch(TpTxGetConnectionNumber(infoStruct->Channel))
    //{
        //case kDiagConnection:
            return DescCopyToCAN(infoStruct);
        //default:
            //(void)memcpy( infoStruct->pDestination, infoStruct->pSource, infoStruct->Length);
            //break;
    //}
    //return 0;
}


/***********************************************************************
* FUNCTION    : vuint8 ApplCopyToCAN(TpCopyToCanInfoStructPtr infoStruct)
* DESCRIPTION : 
* INPUTS      : none
* RETURN      : none
***********************************************************************/
void ApplTpTxNotification(vuint8 tpChannel, vuint8 DataLength)
{/*
    switch(TpTxGetConnectionNumber(tpChannel))
    {
        case kDiagConnection:
            DiagTpMsgTxReady(tpChannel, DataLength);
            break;
        default:
            break;
    }
    */
}

/**************** END OF FILE *****************************************/


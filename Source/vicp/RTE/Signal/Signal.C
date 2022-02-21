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
*-----------------------------------------------------------------------
* 0.1    Aug 11,2016   LIU Chenxi    Initial version
*----------------------------------------------------------------------
* 0.2    Jan 4,2017     ShangQiuju    change CS_SIG_AsyncReceive /CS_SIG_SyncReceive
                                                    parameter plocalSignalCopy from u16* to U8* 
*------------------------------------------------------------------------
* 0.3    Jan 24,2017  ZhangJie  Fix Coverity warnings.
*=====================================================================*/
#include "signal.h"

extern V_asyncreceive SignalaRevProc[E_SIG_TYPE_NUM];
extern V_asyncsend  SignalaSndProc[E_SIG_TYPE_NUM];
extern V_asyncreceive_prehook SignalaRevPreProc[E_SIG_TYPE_NUM];
extern V_asyncreceive_psthook  SignalaRevPstProc[E_SIG_TYPE_NUM];
extern V_asyncsend_prehook SignalaSndPreProc[E_SIG_TYPE_NUM];
extern V_asyncsend_psthook  SignalaSndPstProc[E_SIG_TYPE_NUM];

extern V_syncreceive SignalRevProc[E_SIG_TYPE_NUM];
extern V_syncsend  SignalSndProc[E_SIG_TYPE_NUM];
extern V_syncreceive_prehook SignalRevPreProc[E_SIG_TYPE_NUM];
extern V_syncreceive_psthook  SignalRevPstProc[E_SIG_TYPE_NUM];
extern V_syncsend_prehook SignalSndPreProc[E_SIG_TYPE_NUM];
extern V_syncsend_psthook  SignalSndPstProc[E_SIG_TYPE_NUM];

extern const V_freeze  SignalFreezeProc[E_SIG_TYPE_NUM];
extern const V_unfreeze  SignalUnFreezeProc[E_SIG_TYPE_NUM];

#define SIGNAL_PASS_2
#include "Signal_def.h"
/*---Global-----------------------------------------------------------*/
/***********************************************************************
*  Name        : CS_SIG_Init
*  Description : INIT       
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void CS_SIG_Init(void)
{

}

/***********************************************************************
*  Name        : CS_SIG_DeInit
*  Description : deinit       
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void CS_SIG_DeInit(void)
{

}

/***********************************************************************
*  Name        : CS_SIG_ToGlobalName
*  Description : deinit       
*  Parameter   : SigName,type
*  Returns     : U16
***********************************************************************/
U16  CS_SIG_ToGlobalName(U16 SigName, Sig_SignalType sigtype)
{
    U16 signame=0u;
    U16 i =0u;        	
    if(sigtype>=E_SIG_TYPE_NUM)  
    {   
        signame= 0u;
    }
    else
    {
        for(i=0u;((U16)E_SIG_SIGNALS_NUM>0u)&&(i<(U16)E_SIG_SIGNALS_NUM);i++)
        {
            if((AllSignal[i].type==sigtype)&&(AllSignal[i].sourename==SigName))
            { 
                signame=i;
            }
            else
            {
                /*nothing to do*/
            }
        }
    }
    return signame;
}

/***********************************************************************
*  Name        : CS_SIG_AsyncSend
*  Description :         
*  Parameter   : SigName,plocalSignalCopy
*  Returns     : None
***********************************************************************/
void CS_SIG_AsyncSend(U16 SigName, U8* plocalSignalCopy)
{
    Sig_SignalType sigtype =E_SIG_TYPE_NUM;  
    
    if(((U16)E_SIG_SIGNALS_NUM>0u)&&(SigName<(U16)E_SIG_SIGNALS_NUM))
    {
        sigtype=AllSignal[SigName].type;
        SigName=AllSignal[SigName].sourename;
        SignalaSndPreProc[sigtype](SigName,plocalSignalCopy);
        SignalaSndProc[sigtype](SigName,plocalSignalCopy);
        SignalaSndPstProc[sigtype](SigName,plocalSignalCopy);	
    }
    else
    {
        /*nothing to do*/
    }	
}

/***********************************************************************
*  Name        : CS_SIG_AsyncReceive
*  Description :       
*  Parameter   : SigName,plocalSignalCopy
*  Returns     : U8
***********************************************************************/
U8 CS_SIG_AsyncReceive(U16 SigName, U8* plocalSignalCopy)
{
    U8 ret =(U8)ERR_OK;
    Sig_SignalType sigtype =E_SIG_TYPE_NUM;  
    if(((U16)E_SIG_SIGNALS_NUM>0u)&&(SigName<(U16)E_SIG_SIGNALS_NUM))
    {
        sigtype=AllSignal[SigName].type;
        SigName=AllSignal[SigName].sourename;	
        SignalaRevPreProc[sigtype](SigName,plocalSignalCopy);
        ret=SignalaRevProc[sigtype](SigName,plocalSignalCopy);
        SignalaRevPstProc[sigtype](SigName,plocalSignalCopy);	
    }
    else
    {
        /*nothing to do*/
    }
    return ret;
}

/***********************************************************************
*  Name        : CS_SIG_SyncSend
*  Description : SigName, plocalSignalCopy
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void CS_SIG_SyncSend(U16 SigName, U8* plocalSignalCopy)
{
    Sig_SignalType sigtype =E_SIG_TYPE_NUM;  
    if(((U16)E_SIG_SIGNALS_NUM>0u)&&(SigName<(U16)E_SIG_SIGNALS_NUM))
    {
        sigtype=AllSignal[SigName].type;
        SigName=AllSignal[SigName].sourename;	
        SignalSndPreProc[sigtype](SigName,plocalSignalCopy);
        SignalSndProc[sigtype](SigName,plocalSignalCopy);
        SignalSndPstProc[sigtype](SigName,plocalSignalCopy);	
    }
    else
    {
        /*nothing to do*/
    }
}


/***********************************************************************
*  Name        : CS_SIG_SyncReceive
*  Description :         
*  Parameter   : SigName,plocalSignalCopy
*  Returns     : U8
***********************************************************************/
U8 CS_SIG_SyncReceive(U16 SigName, U8* plocalSignalCopy)
{
    U8 ret =(U8)ERR_OK;
    Sig_SignalType sigtype =E_SIG_TYPE_NUM;  
    if(((U16)E_SIG_SIGNALS_NUM>0u)&&(SigName<(U16)E_SIG_SIGNALS_NUM))
    {
        sigtype=AllSignal[SigName].type;
        SigName=AllSignal[SigName].sourename;	
        SignalRevPreProc[sigtype](SigName,plocalSignalCopy);
        ret=SignalRevProc[sigtype](SigName,plocalSignalCopy);
        SignalRevPstProc[sigtype](SigName,plocalSignalCopy);	
    }
    else
    {
        /*nothing to do*/
    }
    return ret;	
}

/***********************************************************************
*  Name        : CS_SIG_Freeze
*  Description : system alarm tick        
*  Parameter   : SigName
*  Returns     : U8
***********************************************************************/
U8 CS_SIG_Freeze(U16 SigName)
{
    U8 ret =(U8)ERR_OK;
    Sig_SignalType sigtype =E_SIG_TYPE_NUM;  
    if(((U16)E_SIG_SIGNALS_NUM>0u)&&(SigName<(U16)E_SIG_SIGNALS_NUM))
    {
        sigtype=AllSignal[SigName].type;
        SigName=AllSignal[SigName].sourename;	
        SignalFreezeProc[sigtype](SigName);
    }
    else
    {
        /*nothing to do*/
    }
    return ret;
}

/***********************************************************************
*  Name        : CS_SIG_UnFreeze
*  Description : system alarm tick        
*  Parameter   : None
*  Returns     : None
***********************************************************************/
U8 CS_SIG_UnFreeze(U16 SigName)
{
    ERR_TYPE ret =ERR_OK;
    Sig_SignalType sigtype =E_SIG_TYPE_NUM;  
    if(((U16)E_SIG_SIGNALS_NUM>0u)&&(SigName<(U16)E_SIG_SIGNALS_NUM))
    {
        sigtype=AllSignal[SigName].type;
        SigName=AllSignal[SigName].sourename;
        SignalUnFreezeProc[sigtype](SigName);		
    }
    else
    {
        /*nothing to do*/
    }
    return (U8)ret;
}

/***********************************************************************
*  Name        : V_asyncreceive_empty
*  Description :         
*  Parameter   : sig,value
*  Returns     : U8
***********************************************************************/
U8 V_asyncreceive_empty( U16 sig, U8* value)
{
    return (U8)ERR_OK;
}

/***********************************************************************
*  Name        : V_asyncsend_empty
*  Description :         
*  Parameter   : sig,value
*  Returns     : None
***********************************************************************/
void V_asyncsend_empty( U16 sig, U8* value)
{

}

/***********************************************************************
*  Name        : V_asyncreceive_prehook_empty
*  Description :         
*  Parameter   : sig,value
*  Returns     : None
***********************************************************************/
void V_asyncreceive_prehook_empty( U16 sig, U8* value)
{

}

/***********************************************************************
*  Name        : V_asyncreceive_psthook_empty
*  Description :         
*  Parameter   : sig,value
*  Returns     : None
***********************************************************************/
void V_asyncreceive_psthook_empty( U16 sig, U8* value)
{

}

/***********************************************************************
*  Name        : V_asyncsend_prehook_empty
*  Description :         
*  Parameter   : sig,value
*  Returns     : None
***********************************************************************/
void V_asyncsend_prehook_empty( U16 sig, U8* value)
{

}

/***********************************************************************
*  Name        : V_asyncsend_psthook_empty
*  Description :         
*  Parameter   : sig,value
*  Returns     : None
***********************************************************************/
void V_asyncsend_psthook_empty( U16 sig, U8* value)
{

}

/***********************************************************************
*  Name        : V_syncreceive_empty
*  Description :         
*  Parameter   : sig,value
*  Returns     : None
***********************************************************************/
U8 V_syncreceive_empty( U16 sig, U8* value)
{
    return (U8)ERR_OK;
}

/***********************************************************************
*  Name        : V_syncsend_empty
*  Description :         
*  Parameter   : sig,value
*  Returns     : None
***********************************************************************/
void V_syncsend_empty( U16 sig, U8* value)
{

}

/***********************************************************************
*  Name        : V_syncreceive_prehook_empty
*  Description :         
*  Parameter   : sig,value
*  Returns     : None
***********************************************************************/
void V_syncreceive_prehook_empty( U16 sig, U8* value)
{

}

/***********************************************************************
*  Name        : V_syncreceive_psthook_empty
*  Description :         
*  Parameter   : sig,value
*  Returns     : None
***********************************************************************/
void V_syncreceive_psthook_empty( U16 sig, U8* value)
{

}

/***********************************************************************
*  Name        : V_syncsend_prehook_empty
*  Description :         
*  Parameter   : sig,value
*  Returns     : None
***********************************************************************/
void V_syncsend_prehook_empty( U16 sig, U8* value)
{

}

/***********************************************************************
*  Name        : V_syncsend_psthook_empty
*  Description :         
*  Parameter   : sig,value
*  Returns     : None
***********************************************************************/
void V_syncsend_psthook_empty( U16 sig, U8* value)
{

}

/***********************************************************************
*  Name        : V_freeze_empty
*  Description :         
*  Parameter   : sig
*  Returns     : None
***********************************************************************/
void V_freeze_empty( U16 sig)
{

}

/***********************************************************************
*  Name        : V_unfreeze_empty
*  Description :         
*  Parameter   : sig
*  Returns     : None
***********************************************************************/
void V_unfreeze_empty( U16 sig)
{

}

/**************** END OF FILE *****************************************/


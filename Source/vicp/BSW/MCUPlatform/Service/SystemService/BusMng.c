/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.                            *
*                                 All Rights Reserved.                                                     *
*   Department : CT AD                                                                             *
*   AUTHOR         :                                                                       *
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
*------------------------------------------------------------------------
* 0.2    Aug 31,2016            Re-init 
*------------------------------------------------------------------------
* 0.3    Jan 13,2017  ZhangJie  Fix Coverity warnings.
*-----------------------------------------------------------------------
* 0.4   Jan 24,2017   ZhangJie   Fix Coverity warnings phase2.
*=====================================================================*/
#include <Service_HOOKS.h>
#include <Tools.h>
#include <Jobmng.h>
#include "BusMng.H"
#include "OSAPI.h"

#define BUSMNG_PASS_3
#include "BusMng_def.h"

U8 BusMng_au8DevStatus[BUSMNG_DEV_MAXNUM];
BusRequested BusMng_apDevReqFunc[BUSMNG_DEV_MAXNUM];
BusReleased   BusMng_apDevRelFunc[BUSMNG_DEV_MAXNUM];
BOOL BusMng_bBusBusy[BUSMNG_BUS_MAXNUM];
/***********************************************************************
*  Name        : BusMng_Init
*  Description : None
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void BusMng_Init(void)
{
    U8 i =0u;
    for(i=0u; i<(U8)BUSMNG_DEV_MAXNUM; i++)
    {
        BusMng_au8DevStatus[i]=BUSMNG_DEV_IDLE;
        BusMng_apDevReqFunc[i]=NULL;
        BusMng_apDevRelFunc[i]=NULL;
    }

    for(i=0u; i<(U8)BUSMNG_BUS_MAXNUM; i++)
    {
        BusMng_bBusBusy[i]=FALSE;
    }
}

/***********************************************************************
*  Name        : BusMng_DeInit
*  Description : None
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void BusMng_DeInit(void)
{

}

/***********************************************************************
*  Name        : BusMng_Job
*  Description : Bus manager job process
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void BusMng_Job(void)
{
    U8 i=0u;
    U8 BusID=BUSMNG_BUS_MAXNUM;
    U8 ReleaseDevID =BUSMNG_DEV_MAXNUM;
    U8 RequestDevID =BUSMNG_DEV_MAXNUM;
    BOOL isModify=FALSE;

    /*Fisrt handle release bus*/
    OSAPI_LockSchedule();
    for(i=0u; i<(U8)BUSMNG_DEV_MAXNUM; i++)
    {
        if(BusMng_au8DevStatus[i]==(U8)BUSMNG_DEV_RELBUS)
        {
            BusID=BusMng_au8DevCfg[i];
            if(BusMng_bBusBusy[BusID]==TRUE)
            {
                BusMng_au8DevStatus[i]=BUSMNG_DEV_IDLE;
                BusMng_bBusBusy[BusID]=FALSE;
                ReleaseDevID=i;
                isModify=TRUE;
                break;
            }
        }
    }
    OSAPI_UnlockSchedule();

    if(ReleaseDevID!=(U8)BUSMNG_DEV_MAXNUM)
    {
        if(BusMng_apDevRelFunc[ReleaseDevID]!=NULL)
        {
            (*BusMng_apDevRelFunc[ReleaseDevID])();
        }
        else {}
    }
    else {}

    if(isModify==TRUE)
    {
        SysJob_ContinueJob((U8)E_BUSMNG);
        return;
    }

    /*sencond handle request bus*/
    OSAPI_LockSchedule();
    for(i=0u; i<(U8)BUSMNG_DEV_MAXNUM; i++)
    {
        if(BusMng_au8DevStatus[i]==(U8)BUSMNG_DEV_REQBUS)
        {
            BusID=BusMng_au8DevCfg[i];
            if(BusMng_bBusBusy[BusID]==FALSE)
            {
                BusMng_au8DevStatus[i]=BUSMNG_DEV_USEBUS;
                BusMng_bBusBusy[BusID]=TRUE;
                RequestDevID=i;
                isModify=TRUE;
                break;
            }
        }
    }
    OSAPI_UnlockSchedule();

    if(RequestDevID!=(U8)BUSMNG_DEV_MAXNUM)
    {
        if(BusMng_apDevReqFunc[RequestDevID]!=NULL)
        {
            (*BusMng_apDevReqFunc[RequestDevID])();
        }
        else {}
    }
    else {}

    if(isModify==TRUE)
    {
        SysJob_ContinueJob((U8)E_BUSMNG);
    }
    else {}
}

/***********************************************************************
*  Name        : BusMng_IsBuy
*  Description : Request bus resource
*  Parameter   : None
*  Returns     : None
***********************************************************************/
BOOL BusMng_IsBuy(U8 DevId)
{
    BOOL bRet=FALSE;

    if(DevId<(U8)BUSMNG_DEV_MAXNUM)
    {
        if(BusMng_au8DevStatus[DevId]!=(U8)BUSMNG_DEV_IDLE)
        {
            bRet=TRUE;
        }
    }
    else {}

    return  bRet;
}


/***********************************************************************
*  Name        : BusMng_Request
*  Description : Request bus resource
*  Parameter   : None
*  Returns     : None
***********************************************************************/
BusMng_RequestBusType BusMng_Request(U8 DevId, BOOL isWaiting,BusRequested fBusRequested)
{
    BOOL isOK=FALSE;
    BusMng_RequestBusType ReqRet=BUSMNG_REQUEST_ACCEPTED;

    /*TODO:*/
    (void)isWaiting;

    if(DevId>=(U8)BUSMNG_DEV_MAXNUM)
    {
        ReqRet=BUSMNG_REQUEST_FAIL;
    }
    else
    {
        /*TODO: add if release no finished*/
        OSAPI_LockSchedule();
        if(BusMng_au8DevStatus[DevId]==(U8)BUSMNG_DEV_IDLE)
        {
            BusMng_au8DevStatus[DevId]=BUSMNG_DEV_REQBUS;
            BusMng_apDevReqFunc[DevId]=fBusRequested;
            isOK= TRUE;
        }
        else if(BusMng_au8DevStatus[DevId]==(U8)BUSMNG_DEV_USEBUS)
        {
            ReqRet= BUSMNG_REQUEST_FINISHED;
            /*bus is use or request bus or request release, than reject request*/
        }
        else if(BusMng_au8DevStatus[DevId]==(U8)BUSMNG_DEV_REQBUS)
        {
            ReqRet= BUSMNG_REQUEST_REQUESTED;
            /*bus is use or request bus or request release, than reject request*/
        }
        else if(BusMng_au8DevStatus[DevId]==(U8)BUSMNG_DEV_RELBUS)
        {
            ReqRet= BUSMNG_REQUEST_FAIL;
        }
        else {}
        OSAPI_UnlockSchedule();

        if(isOK==TRUE)
        {
            SysJob_StartJob((U8)E_BUSMNG);
        }
        else {}
    }
    return ReqRet;
}

/***********************************************************************
*  Name        : BusMng_Release
*  Description : release bus resource
*  Parameter   : None
*  Returns     : None
***********************************************************************/
BusMng_RequestBusType BusMng_Release(U8 DevId, BOOL isWaiting,BusReleased fBusReleased)
{
    BOOL isOK=FALSE;
    BusMng_RequestBusType ReqRet=BUSMNG_REQUEST_ACCEPTED;
    /*TODO:*/
    (void)isWaiting;
    if(DevId>=(U8)BUSMNG_DEV_MAXNUM)
    {
        ReqRet=BUSMNG_REQUEST_FAIL;
    }
    else
    {

        OSAPI_LockSchedule();
        if(BusMng_au8DevStatus[DevId]==(U8)BUSMNG_DEV_USEBUS)
        {
            BusMng_au8DevStatus[DevId]=BUSMNG_DEV_RELBUS;
            BusMng_apDevRelFunc[DevId]=fBusReleased;
            isOK=TRUE;
        }
        else if(BusMng_au8DevStatus[DevId]==(U8)BUSMNG_DEV_IDLE)
        {
            ReqRet= BUSMNG_REQUEST_FINISHED;
            /*bus is use or request bus or request release, than reject request*/
        }
        else if(BusMng_au8DevStatus[DevId]==(U8)BUSMNG_DEV_RELBUS)
        {
            ReqRet= BUSMNG_REQUEST_REQUESTED;
            /*bus is use or request bus or request release, than reject request*/
        }
        else if(BusMng_au8DevStatus[DevId]==(U8)BUSMNG_DEV_REQBUS)
        {
            ReqRet= BUSMNG_REQUEST_FAIL;
        }
        else {}
        OSAPI_UnlockSchedule();

        if(isOK==TRUE)
        {
            SysJob_StartJob((U8)E_BUSMNG);
        }
        else {}
    }
    return ReqRet;
}
/**************** END OF FILE *****************************************/

